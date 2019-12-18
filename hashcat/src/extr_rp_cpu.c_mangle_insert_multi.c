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
 int RP_PASSWORD_SIZE ; 
 int RULE_RC_REJECT_ERROR ; 
 int RULE_RC_SYNTAX_ERROR ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static int mangle_insert_multi (char arr[RP_PASSWORD_SIZE], int arr_len, int arr_pos, char arr2[RP_PASSWORD_SIZE], int arr2_len, int arr2_pos, int arr2_cpy)
{
  if ((arr_len + arr2_cpy) > RP_PASSWORD_SIZE) return (RULE_RC_REJECT_ERROR);

  if (arr_pos > arr_len) return (RULE_RC_REJECT_ERROR);

  if (arr2_pos > arr2_len) return (RULE_RC_REJECT_ERROR);

  if ((arr2_pos + arr2_cpy) > arr2_len) return (RULE_RC_REJECT_ERROR);

  if (arr2_cpy < 1) return (RULE_RC_SYNTAX_ERROR);

  memmove (arr2, arr2 + arr2_pos, arr2_len - arr2_pos);

  memcpy  (arr2 + arr2_cpy, arr + arr_pos, arr_len - arr_pos);

  memcpy  (arr + arr_pos, arr2, arr_len - arr_pos + arr2_cpy);

  return (arr_len + arr2_cpy);
}