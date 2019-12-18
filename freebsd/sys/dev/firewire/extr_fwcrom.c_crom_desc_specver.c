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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ CSRVAL_1394TA ; 
 scalar_t__ CSRVAL_ANSIT10 ; 
#define  CSRVAL_T10SBP2 137 
#define  CSR_PROTAVC 136 
#define  CSR_PROTCAL 135 
#define  CSR_PROTCAM104 134 
#define  CSR_PROTCAM120 133 
#define  CSR_PROTCAM130 132 
#define  CSR_PROTDPP 131 
#define  CSR_PROTEHS 130 
#define  CSR_PROTHAVI 129 
#define  CSR_PROTIICP 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
crom_desc_specver(uint32_t spec, uint32_t ver, char *buf, int len)
{
	char *s = NULL;

	if (spec == CSRVAL_ANSIT10 || spec == 0) {
		switch (ver) {
		case CSRVAL_T10SBP2:
			s = "SBP-2";
			break;
		default:
			if (spec != 0)
				s = "unknown ANSIT10";
		}
	}
	if (spec == CSRVAL_1394TA || spec == 0) {
		switch (ver) {
		case CSR_PROTAVC:
			s = "AV/C";
			break;
		case CSR_PROTCAL:
			s = "CAL";
			break;
		case CSR_PROTEHS:
			s = "EHS";
			break;
		case CSR_PROTHAVI:
			s = "HAVi";
			break;
		case CSR_PROTCAM104:
			s = "1394 Cam 1.04";
			break;
		case CSR_PROTCAM120:
			s = "1394 Cam 1.20";
			break;
		case CSR_PROTCAM130:
			s = "1394 Cam 1.30";
			break;
		case CSR_PROTDPP:
			s = "1394 Direct print";
			break;
		case CSR_PROTIICP:
			s = "Industrial & Instrument";
			break;
		default:
			if (spec != 0)
				s = "unknown 1394TA";
		}
	}
	if (s != NULL)
		snprintf(buf, len, "%s", s);
}