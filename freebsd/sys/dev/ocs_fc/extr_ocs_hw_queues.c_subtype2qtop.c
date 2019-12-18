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
typedef  int tok_subtype_e ;
typedef  int /*<<< orphan*/  ocs_hw_qtop_entry_e ;

/* Variables and functions */
 int /*<<< orphan*/  QTOP_CQ ; 
 int /*<<< orphan*/  QTOP_EQ ; 
 int /*<<< orphan*/  QTOP_MQ ; 
 int /*<<< orphan*/  QTOP_RQ ; 
 int /*<<< orphan*/  QTOP_WQ ; 
#define  TOK_SUB_CQ 132 
#define  TOK_SUB_EQ 131 
#define  TOK_SUB_MQ 130 
#define  TOK_SUB_RQ 129 
#define  TOK_SUB_WQ 128 

__attribute__((used)) static ocs_hw_qtop_entry_e
subtype2qtop(tok_subtype_e q)
{
	switch(q) {
	case TOK_SUB_EQ:	return QTOP_EQ;
	case TOK_SUB_CQ:	return QTOP_CQ;
	case TOK_SUB_RQ:	return QTOP_RQ;
	case TOK_SUB_MQ:	return QTOP_MQ;
	case TOK_SUB_WQ:	return QTOP_WQ;
	default:
		break;
	}
	return 0;
}