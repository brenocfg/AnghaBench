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
struct TYPE_4__ {int /*<<< orphan*/  found_entry; } ;
typedef  TYPE_1__ MMDB_lookup_result_s ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int MMDB_SUCCESS ; 
 TYPE_1__ MMDB_lookup_string (int /*<<< orphan*/ ,char const*,int*,int*) ; 
 int /*<<< orphan*/  MMDB_strerror (int) ; 
 int /*<<< orphan*/  mmdb ; 

__attribute__((used)) static int
geoip_lookup (MMDB_lookup_result_s * res, const char *ip)
{
  int gai_err, mmdb_err;

  *res = MMDB_lookup_string (mmdb, ip, &gai_err, &mmdb_err);
  if (0 != gai_err)
    return 1;

  if (MMDB_SUCCESS != mmdb_err)
    FATAL ("Error from libmaxminddb: %s\n", MMDB_strerror (mmdb_err));

  if (!(*res).found_entry)
    return 1;

  return 0;
}