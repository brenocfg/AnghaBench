#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  set; int /*<<< orphan*/  etlv; int /*<<< orphan*/  name; } ;
struct nptv6_cfg {int /*<<< orphan*/  name; TYPE_1__ no; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_ARRAY_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IPFW_TLV_NPTV6_NAME ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NPTV6STATS ; 
 struct nptv6_cfg* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct nptv6_cfg *
nptv6_alloc_config(const char *name, uint8_t set)
{
	struct nptv6_cfg *cfg;

	cfg = malloc(sizeof(struct nptv6_cfg), M_IPFW, M_WAITOK | M_ZERO);
	COUNTER_ARRAY_ALLOC(cfg->stats, NPTV6STATS, M_WAITOK);
	cfg->no.name = cfg->name;
	cfg->no.etlv = IPFW_TLV_NPTV6_NAME;
	cfg->no.set = set;
	strlcpy(cfg->name, name, sizeof(cfg->name));
	return (cfg);
}