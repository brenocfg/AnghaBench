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
#define  SM_FIRSTINT 130 
#define  SM_HASH 129 
#define  SM_HASHDOT 128 
 int /*<<< orphan*/  assert (int) ; 
 unsigned long long extract_num (char const* const,unsigned long long,int /*<<< orphan*/ *) ; 
 unsigned long long hash_key (char const* const,unsigned long long) ; 
 int split_mode ; 
 unsigned long long split_modulo ; 
 unsigned long long split_rem ; 
 unsigned long long strlen (char const* const) ; 

int conv_key (const char* const key) {
  unsigned long long id, i = -1;
  switch (split_mode) {
    case SM_HASH:
      id = hash_key(key, strlen(key));
      break;
    case SM_FIRSTINT:
      id = extract_num(key, strlen(key), NULL);
      break;
    case SM_HASHDOT:
      for (i = 0; key[i] && key[i] != '.'; i++)
        ;
      id = hash_key(key, i);
      break;
    default:
      assert("unknown split mode!" && 0);
  }
  return id % split_modulo == split_rem ? 0 : -1;
}