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

/* Variables and functions */
 scalar_t__ buffer_create_data (char*,int) ; 
 scalar_t__ buffer_delete (scalar_t__) ; 
 scalar_t__ inbuf ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* zzemalloc (int) ; 

void do_rpc_parse (const char *s, int len) { /* {{{ */
  char *ans = zzemalloc (len);
  memcpy (ans, s, len);
  if (inbuf) {
    inbuf = buffer_delete (inbuf);      
  }
  inbuf = buffer_create_data (ans, len);
}