#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connection {int /*<<< orphan*/  Tmp; } ;
typedef  int /*<<< orphan*/  nb_iterator_t ;

/* Variables and functions */
 int MAX_AUX_USERS ; 
 int VALUE_BUFF_SIZE ; 
 int* aux_userlist ; 
 int aux_userlist_size ; 
 int aux_userlist_tag ; 
 int nbit_read_in (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ nbit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tag_id ; 
 int tag_len ; 
 int* value_buff ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int) ; 

int load_temp_data (struct connection *c) {
  nb_iterator_t it;
  tag_len = 0;
  aux_userlist_size = aux_userlist_tag = 0;
  if (!c->Tmp || nbit_set (&it, c->Tmp) < 0 || nbit_read_in (&it, &tag_id, 4) < 4 || !tag_id) {
    return tag_id = 0;
  }
  if (tag_id < 0) {
    int len = nbit_read_in (&it, aux_userlist, MAX_AUX_USERS * 4);
    if (len < 0 || (len & 3) || len == MAX_AUX_USERS * 4) {
      return tag_id = 0;
    }
    aux_userlist_size = (len >> 2);
    aux_userlist_tag = tag_id;
    vkprintf (2, "restoring %d words of temp userlist data with tag %d\n", aux_userlist_size, tag_id);
    return tag_id = 0;
  }
  int len = nbit_read_in (&it, value_buff, VALUE_BUFF_SIZE - 1);
  if (len <= 0 || len >= VALUE_BUFF_SIZE - 1) {
    return tag_id = 0;
  }
  value_buff[len] = 0;
  tag_len = len;
  vkprintf (2, "restoring %d bytes of temp data with tag %d\n", len, tag_id);
  return tag_id;
}