#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  int /*<<< orphan*/  plist_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* on_error ) (TYPE_1__*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  plist_to_xml (int /*<<< orphan*/ ,char**,int*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

rpc_status rpc_args_to_xml(rpc_t self,
    const void *args_obj, char **to_xml, bool should_trim) {
  if (!args_obj || !to_xml) {
    return RPC_ERROR;
  }
  *to_xml = NULL;
  uint32_t length = 0;
  plist_to_xml((plist_t)args_obj, to_xml, &length);
  if (!*to_xml || !length) {
    return self->on_error(self, "plist_to_xml failed");
  }
  if (should_trim) {
    char *head = strstr(*to_xml, "<plist");
    head = (head ? strchr(head, '>') : NULL);
    if (head) {
      while (*++head == '\n') {
      }
      char *tail = *to_xml + length;
      while (tail > head && (!*tail || *tail == '\n')) {
        tail--;
      }
      if (tail-head >= 8 && !strncmp(tail-7, "</plist>", 8)) {
        tail -= 8;
        char *new_xml = (char *)malloc((tail - head + 1) * sizeof(char));
        strncpy(new_xml, head, tail - head);
        new_xml[tail - head] = '\0';
        free(*to_xml);
        *to_xml = new_xml;
      }
    }
  }
  return RPC_SUCCESS;
}