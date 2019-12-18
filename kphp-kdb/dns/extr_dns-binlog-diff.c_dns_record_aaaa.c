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
struct lev_dns_record_aaaa {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int add_record (struct lev_dns_record_aaaa*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_type_aaaa ; 

__attribute__((used)) static int dns_record_aaaa (struct lev_dns_record_aaaa *E, int s) {
  return add_record (E, s, dns_type_aaaa, E->name);
}