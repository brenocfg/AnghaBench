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
 int SIZE (char const* const*) ; 

char const *
hci_manufacturer2str(int m)
{
	static char const * const	t[] = {
		/* 0000 */ "Ericsson Technology Licensing",
		/* 0001 */ "Nokia Mobile Phones",
		/* 0002 */ "Intel Corp.",
		/* 0003 */ "IBM Corp.",
		/* 0004 */ "Toshiba Corp.",
		/* 0005 */ "3Com",
		/* 0006 */ "Microsoft",
		/* 0007 */ "Lucent",
		/* 0008 */ "Motorola",
		/* 0009 */ "Infineon Technologies AG",
		/* 0010 */ "Cambridge Silicon Radio",
		/* 0011 */ "Silicon Wave",
		/* 0012 */ "Digianswer A/S",
		/* 0013 */ "Texas Instruments Inc.",
		/* 0014 */ "Parthus Technologies Inc.",
		/* 0015 */ "Broadcom Corporation",
		/* 0016 */ "Mitel Semiconductor",
		/* 0017 */ "Widcomm, Inc.",
		/* 0018 */ "Zeevo, Inc.",
		/* 0019 */ "Atmel Corporation",
		/* 0020 */ "Mitsubishi Electric Corporation",
		/* 0021 */ "RTX Telecom A/S",
		/* 0022 */ "KC Technology Inc.",
		/* 0023 */ "Newlogic",
		/* 0024 */ "Transilica, Inc.",
		/* 0025 */ "Rohde & Schwartz GmbH & Co. KG",
		/* 0026 */ "TTPCom Limited",
		/* 0027 */ "Signia Technologies, Inc.",
		/* 0028 */ "Conexant Systems Inc.",
		/* 0029 */ "Qualcomm",
		/* 0030 */ "Inventel",
		/* 0031 */ "AVM Berlin",
		/* 0032 */ "BandSpeed, Inc.",
		/* 0033 */ "Mansella Ltd",
		/* 0034 */ "NEC Corporation",
		/* 0035 */ "WavePlus Technology Co., Ltd.",
		/* 0036 */ "Alcatel",
		/* 0037 */ "Philips Semiconductors",
		/* 0038 */ "C Technologies",
		/* 0039 */ "Open Interface",
		/* 0040 */ "R F Micro Devices",
		/* 0041 */ "Hitachi Ltd",
		/* 0042 */ "Symbol Technologies, Inc.",
		/* 0043 */ "Tenovis",
		/* 0044 */ "Macronix International Co. Ltd.",
		/* 0045 */ "GCT Semiconductor",
		/* 0046 */ "Norwood Systems",
		/* 0047 */ "MewTel Technology Inc.",
		/* 0048 */ "ST Microelectronics",
		/* 0049 */ "Synopsys",
		/* 0050 */ "Red-M (Communications) Ltd",
		/* 0051 */ "Commil Ltd",
		/* 0052 */ "Computer Access Technology Corporation (CATC)",
		/* 0053 */ "Eclipse (HQ Espana) S.L.",
		/* 0054 */ "Renesas Technology Corp.",
		/* 0055 */ "Mobilian Corporation",
		/* 0056 */ "Terax",
		/* 0057 */ "Integrated System Solution Corp.",
		/* 0058 */ "Matsushita Electric Industrial Co., Ltd.",
		/* 0059 */ "Gennum Corporation",
		/* 0060 */ "Research In Motion",
		/* 0061 */ "IPextreme, Inc.",
		/* 0062 */ "Systems and Chips, Inc",
		/* 0063 */ "Bluetooth SIG, Inc",
		/* 0064 */ "Seiko Epson Corporation"
        };

	return (m >= SIZE(t)? "?" : t[m]);
}