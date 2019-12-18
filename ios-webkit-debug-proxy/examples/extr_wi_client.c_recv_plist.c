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
typedef  int /*<<< orphan*/  wi_t ;
typedef  int /*<<< orphan*/  wi_status ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  plist_t ;

/* Variables and functions */
 int /*<<< orphan*/  WI_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  plist_to_xml (int /*<<< orphan*/  const,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts (char*) ; 

wi_status recv_plist(wi_t wi, const plist_t rpc_dict) {
  char *xml = NULL;
  uint32_t length = 0;
  plist_to_xml(rpc_dict, &xml, &length);
  puts(xml);
  free(xml);
  return WI_SUCCESS;
}