#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * qpage_count; int /*<<< orphan*/ * max_qentries; int /*<<< orphan*/ * max_qcount; } ;
struct TYPE_5__ {TYPE_1__ config; } ;
typedef  TYPE_2__ sli4_t ;
typedef  size_t sli4_qtype_e ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;

/* Variables and functions */
#define  SLI_QTYPE_CQ 132 
#define  SLI_QTYPE_EQ 131 
#define  SLI_QTYPE_MQ 130 
#define  SLI_QTYPE_RQ 129 
#define  SLI_QTYPE_WQ 128 
 int /*<<< orphan*/  ocs_ddump_endsection (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  ocs_ddump_section (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  ocs_ddump_value (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_ddump_sli_q_fields(ocs_textbuf_t *textbuf, sli4_t *sli4, sli4_qtype_e qtype)
{
	char * q_desc;

	switch(qtype) {
	case SLI_QTYPE_EQ: q_desc = "EQ"; break;
	case SLI_QTYPE_CQ: q_desc = "CQ"; break;
	case SLI_QTYPE_MQ: q_desc = "MQ"; break;
	case SLI_QTYPE_WQ: q_desc = "WQ"; break;
	case SLI_QTYPE_RQ: q_desc = "RQ"; break;
	default: q_desc = "unknown"; break;
	}

	ocs_ddump_section(textbuf, q_desc, qtype);

	ocs_ddump_value(textbuf, "max_qcount", "%d", sli4->config.max_qcount[qtype]);
	ocs_ddump_value(textbuf, "max_qentries", "%d", sli4->config.max_qentries[qtype]);
	ocs_ddump_value(textbuf, "qpage_count", "%d", sli4->config.qpage_count[qtype]);
	ocs_ddump_endsection(textbuf, q_desc, qtype);
}