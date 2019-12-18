#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct account_type {int withdraw_code; int access_code; int create_code; } ;
typedef  int money_auth_code_t ;
struct TYPE_3__ {int withdraw_code; int access_code; } ;
typedef  TYPE_1__ account_t ;

/* Variables and functions */
 struct account_type** AccTypes ; 
 unsigned int MAX_ACCOUNT_TYPE ; 
 scalar_t__ check_signature (char*,char*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,int,long long,int) ; 
 TYPE_1__* get_account (int,long long) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int verbosity ; 

money_auth_code_t check_auth_code (char *auth_signature, char *signed_string, int acc_type_id, long long acc_id) {
  account_t *A = get_account (acc_type_id, acc_id);
  int L = strlen (signed_string);
  static char temp[8192];
  if (verbosity > 1) {
    fprintf (stderr, "check_auth_code: signature='%.32s', signed_string='%s', acc_type=%d, acc_id=%lld, secret=%016llx\n", auth_signature, signed_string, acc_type_id, acc_id, A ? A->withdraw_code : 0);
  }
  if (L >= 4096 || (unsigned) acc_type_id > MAX_ACCOUNT_TYPE) {
    return -1;
  }
  memcpy (temp, signed_string, L);
  if (acc_id && A) {
    if (check_signature (auth_signature, temp, L, A->withdraw_code)) {
      return A->withdraw_code;
    }
    if (check_signature (auth_signature, temp, L, A->access_code)) {
      return A->access_code;
    }
  }
  struct account_type *AT = AccTypes[acc_type_id];
  if (!AT) {
    return -1;
  }
  if (check_signature (auth_signature, temp, L, AT->withdraw_code)) {
    return AT->withdraw_code;
  }
  if (check_signature (auth_signature, temp, L, AT->access_code)) {
    return AT->access_code;
  }
  if (check_signature (auth_signature, temp, L, AT->create_code)) {
    return AT->create_code;
  }
  return -1;
}