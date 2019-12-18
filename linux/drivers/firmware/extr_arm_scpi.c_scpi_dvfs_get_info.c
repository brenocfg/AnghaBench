#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct scpi_opp {void* m_volt; void* freq; } ;
struct scpi_dvfs_info {int count; int latency; struct scpi_opp* opps; } ;
struct dvfs_info {int opp_count; TYPE_1__* opps; int /*<<< orphan*/  latency; } ;
typedef  int /*<<< orphan*/  domain ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {struct scpi_dvfs_info** dvfs; } ;
struct TYPE_3__ {int /*<<< orphan*/  m_volt; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_DVFS_INFO ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct scpi_dvfs_info* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MAX_DVFS_DOMAINS ; 
 struct scpi_opp* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scpi_dvfs_info*) ; 
 struct scpi_dvfs_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opp_cmp_func ; 
 TYPE_2__* scpi_info ; 
 int scpi_send_message (int /*<<< orphan*/ ,size_t*,int,struct dvfs_info*,int) ; 
 int /*<<< orphan*/  sort (struct scpi_opp*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct scpi_dvfs_info *scpi_dvfs_get_info(u8 domain)
{
	struct scpi_dvfs_info *info;
	struct scpi_opp *opp;
	struct dvfs_info buf;
	int ret, i;

	if (domain >= MAX_DVFS_DOMAINS)
		return ERR_PTR(-EINVAL);

	if (scpi_info->dvfs[domain])	/* data already populated */
		return scpi_info->dvfs[domain];

	ret = scpi_send_message(CMD_GET_DVFS_INFO, &domain, sizeof(domain),
				&buf, sizeof(buf));
	if (ret)
		return ERR_PTR(ret);

	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return ERR_PTR(-ENOMEM);

	info->count = buf.opp_count;
	info->latency = le16_to_cpu(buf.latency) * 1000; /* uS to nS */

	info->opps = kcalloc(info->count, sizeof(*opp), GFP_KERNEL);
	if (!info->opps) {
		kfree(info);
		return ERR_PTR(-ENOMEM);
	}

	for (i = 0, opp = info->opps; i < info->count; i++, opp++) {
		opp->freq = le32_to_cpu(buf.opps[i].freq);
		opp->m_volt = le32_to_cpu(buf.opps[i].m_volt);
	}

	sort(info->opps, info->count, sizeof(*opp), opp_cmp_func, NULL);

	scpi_info->dvfs[domain] = info;
	return info;
}