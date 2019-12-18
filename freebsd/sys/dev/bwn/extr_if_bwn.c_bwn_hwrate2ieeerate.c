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
#define  BWN_CCK_RATE_11MB 139 
#define  BWN_CCK_RATE_1MB 138 
#define  BWN_CCK_RATE_2MB 137 
#define  BWN_CCK_RATE_5MB 136 
#define  BWN_OFDM_RATE_12MB 135 
#define  BWN_OFDM_RATE_18MB 134 
#define  BWN_OFDM_RATE_24MB 133 
#define  BWN_OFDM_RATE_36MB 132 
#define  BWN_OFDM_RATE_48MB 131 
#define  BWN_OFDM_RATE_54MB 130 
#define  BWN_OFDM_RATE_6MB 129 
#define  BWN_OFDM_RATE_9MB 128 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
bwn_hwrate2ieeerate(int rate)
{

	switch (rate) {
	case BWN_CCK_RATE_1MB:
		return (2);
	case BWN_CCK_RATE_2MB:
		return (4);
	case BWN_CCK_RATE_5MB:
		return (11);
	case BWN_CCK_RATE_11MB:
		return (22);
	case BWN_OFDM_RATE_6MB:
		return (12);
	case BWN_OFDM_RATE_9MB:
		return (18);
	case BWN_OFDM_RATE_12MB:
		return (24);
	case BWN_OFDM_RATE_18MB:
		return (36);
	case BWN_OFDM_RATE_24MB:
		return (48);
	case BWN_OFDM_RATE_36MB:
		return (72);
	case BWN_OFDM_RATE_48MB:
		return (96);
	case BWN_OFDM_RATE_54MB:
		return (108);
	default:
		printf("Ooops\n");
		return (0);
	}
}