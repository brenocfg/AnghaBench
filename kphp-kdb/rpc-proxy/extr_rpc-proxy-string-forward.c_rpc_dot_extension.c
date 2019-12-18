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
 int /*<<< orphan*/  RPC_FUN_NEXT ; 
 char* memchr (char const*,char,int) ; 

int rpc_dot_extension (void **IP, void **Data) {
  const char *key = *Data;
  int key_len = (long)*(Data + 1);
  char *dot_pos = memchr (key, '.', key_len);
  if (dot_pos) {
    *(Data + 1) = (void *)(long)(dot_pos - key);
  }
  RPC_FUN_NEXT;
}