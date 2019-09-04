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
struct tl_token {int dummy; } ;

/* Variables and functions */
 scalar_t__ isupper (char const) ; 
 char* tl_token_skip_namespace (struct tl_token*) ; 

__attribute__((used)) static int tl_token_is_type_name (struct tl_token *T) {
  const char *r = tl_token_skip_namespace (T);
  return isupper(r[0]) ? 1 : 0;
}