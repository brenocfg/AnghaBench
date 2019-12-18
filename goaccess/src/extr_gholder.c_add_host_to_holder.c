#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int s_addr; int* s6_addr; } ;
struct in6_addr {int s_addr; int* s6_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  anonymize_ip; } ;
struct TYPE_6__ {int /*<<< orphan*/  module; } ;
typedef  int /*<<< orphan*/  GRawDataType ;
typedef  int /*<<< orphan*/  GRawDataItem ;
typedef  int /*<<< orphan*/  GPanel ;
typedef  TYPE_1__ GHolder ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  add_data_to_holder (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 TYPE_3__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,struct in_addr*,char*,int) ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,struct in_addr*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int set_data_hits_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int*) ; 
 int /*<<< orphan*/  set_host (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*,char*,int) ; 

__attribute__((used)) static void
add_host_to_holder (GRawDataItem item, GHolder * h, GRawDataType type,
                    const GPanel * panel)
{
  char buf4[INET_ADDRSTRLEN];
  char buf6[INET6_ADDRSTRLEN];
  char *data = NULL;
  int hits = 0;
  unsigned i;

  struct in6_addr addr6, mask6, nwork6;
  struct in_addr addr4, mask4, nwork4;

  const char *m4 = "255.255.255.0";
  const char *m6 = "ffff:ffff:ffff:ffff:0000:0000:0000:0000";

  if (set_data_hits_keys (h->module, item, type, &data, &hits) == 1)
    return;

  if (!conf.anonymize_ip) {
    add_data_to_holder (item, h, type, panel);
    free (data);
    return;
  }

  if (1 == inet_pton (AF_INET, data, &addr4)) {
    if (1 == inet_pton (AF_INET, m4, &mask4)) {
      memset (buf4, 0, sizeof *buf4);
      nwork4.s_addr = addr4.s_addr & mask4.s_addr;

      if (inet_ntop (AF_INET, &nwork4, buf4, INET_ADDRSTRLEN) != NULL) {
        set_host (item, h, panel, buf4, hits);
        free (data);
      }
    }
  } else if (1 == inet_pton (AF_INET6, data, &addr6)) {
    if (1 == inet_pton (AF_INET6, m6, &mask6)) {
      memset (buf6, 0, sizeof *buf6);
      for (i = 0; i < 16; i++) {
        nwork6.s6_addr[i] = addr6.s6_addr[i] & mask6.s6_addr[i];
      }

      if (inet_ntop (AF_INET6, &nwork6, buf6, INET6_ADDRSTRLEN) != NULL) {
        set_host (item, h, panel, buf6, hits);
        free (data);
      }
    }
  }
}