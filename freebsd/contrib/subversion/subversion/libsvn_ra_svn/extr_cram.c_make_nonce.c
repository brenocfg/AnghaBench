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
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_generate_random_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  apr_time_now () ; 

__attribute__((used)) static apr_status_t make_nonce(apr_uint64_t *nonce)
{
#if APR_HAS_RANDOM
  return apr_generate_random_bytes((unsigned char *) nonce, sizeof(*nonce));
#else
  *nonce = apr_time_now();
  return APR_SUCCESS;
#endif
}