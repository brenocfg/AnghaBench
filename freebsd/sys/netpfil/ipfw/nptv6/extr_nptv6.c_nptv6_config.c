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
struct sockopt_data {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int
nptv6_config(struct ip_fw_chain *chain, ip_fw3_opheader *op,
    struct sockopt_data *sd)
{

	return (EOPNOTSUPP);
}