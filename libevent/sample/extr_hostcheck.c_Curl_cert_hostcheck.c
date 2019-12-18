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
 scalar_t__ CURL_HOST_MATCH ; 
 scalar_t__ Curl_raw_equal (char const*,char const*) ; 
 scalar_t__ hostmatch (char const*,char const*) ; 

int Curl_cert_hostcheck(const char *match_pattern, const char *hostname)
{
  if(!match_pattern || !*match_pattern ||
      !hostname || !*hostname) /* sanity check */
    return 0;

  if(Curl_raw_equal(hostname, match_pattern)) /* trivial case */
    return 1;

  if(hostmatch(hostname,match_pattern) == CURL_HOST_MATCH)
    return 1;
  return 0;
}