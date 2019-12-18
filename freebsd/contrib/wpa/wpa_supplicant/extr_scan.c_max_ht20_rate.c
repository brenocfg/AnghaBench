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

__attribute__((used)) static unsigned int max_ht20_rate(int snr)
{
	if (snr < 6)
		return 6500; /* HT20 MCS0 */
	if (snr < 8)
		return 13000; /* HT20 MCS1 */
	if (snr < 13)
		return 19500; /* HT20 MCS2 */
	if (snr < 17)
		return 26000; /* HT20 MCS3 */
	if (snr < 20)
		return 39000; /* HT20 MCS4 */
	if (snr < 23)
		return 52000; /* HT20 MCS5 */
	if (snr < 24)
		return 58500; /* HT20 MCS6 */
	return 65000; /* HT20 MCS7 */
}