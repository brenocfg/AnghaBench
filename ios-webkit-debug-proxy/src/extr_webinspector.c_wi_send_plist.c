#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* wi_t ;
typedef  scalar_t__ wi_status ;
typedef  TYPE_2__* wi_private_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/ * plist_t ;
struct TYPE_7__ {scalar_t__ partials_supported; } ;
struct TYPE_6__ {scalar_t__ (* send_packet ) (TYPE_1__*,char*,size_t) ;TYPE_2__* private_state; } ;

/* Variables and functions */
 scalar_t__ MAX_RPC_LEN ; 
 scalar_t__ WI_ERROR ; 
 scalar_t__ WI_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  plist_dict_set_item (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * plist_new_data (char*,scalar_t__) ; 
 int /*<<< orphan*/ * plist_new_dict () ; 
 int /*<<< orphan*/  plist_to_bin (int /*<<< orphan*/ *,char**,scalar_t__*) ; 
 scalar_t__ stub1 (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  wi_on_debug (TYPE_1__*,char*,char*,size_t) ; 

wi_status wi_send_plist(wi_t self, plist_t rpc_dict) {
  wi_private_t my = self->private_state;
  char *rpc_bin = NULL;
  uint32_t rpc_len = 0;
  plist_to_bin(rpc_dict, &rpc_bin, &rpc_len);
  // if our message is <8k, we'll send a single final_msg,
  // otherwise we'll send <8k partial_msg "chunks" then a final_msg "chunk"
  wi_status ret = WI_ERROR;
  uint32_t i;
  for (i = 0; ; i += MAX_RPC_LEN) {
    bool is_partial = false;
    char *data = NULL;
    uint32_t data_len = 0;
    if (!my->partials_supported) {
      data = rpc_bin;
      data_len = rpc_len;
      rpc_bin = NULL;
    } else {
      is_partial = (rpc_len - i > MAX_RPC_LEN);
      plist_t wi_dict = plist_new_dict();
      plist_t wi_rpc = plist_new_data(rpc_bin + i,
          (is_partial ? MAX_RPC_LEN : rpc_len - i));
      plist_dict_set_item(wi_dict,
          (is_partial ? "WIRPartialMessageKey" : "WIRFinalMessageKey"), wi_rpc);
      plist_to_bin(wi_dict, &data, &data_len);
      plist_free(wi_dict);
      wi_dict = NULL;
      wi_rpc = NULL; // freed by wi_dict
      if (!data) {
        break;
      }
    }

    size_t length = data_len + 4;
    char *out_head = (char*)malloc(length * sizeof(char));
    if (!out_head) {
      if (my->partials_supported) {
        free(data);
      }
      break;
    }
    char *out_tail = out_head;

    // write big-endian int
    *out_tail++ = ((data_len >> 24) & 0xFF);
    *out_tail++ = ((data_len >> 16) & 0xFF);
    *out_tail++ = ((data_len >> 8) & 0xFF);
    *out_tail++ = (data_len & 0xFF);

    // write data
    memcpy(out_tail, data, data_len);
    free(data);

    wi_on_debug(self, "wi.send_packet", out_head, length);
    wi_status not_sent = self->send_packet(self, out_head, length);
    free(out_head);
    if (not_sent) {
      break;
    }

    if (!is_partial) {
      ret = WI_SUCCESS;
      break;
    }
  }
  free(rpc_bin);
  return ret;
}