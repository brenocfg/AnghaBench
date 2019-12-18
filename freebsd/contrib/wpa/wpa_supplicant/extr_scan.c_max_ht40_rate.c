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

__attribute__((used)) static unsigned int max_ht40_rate(int snr)
{
	if (snr < 3)
		return 13500; /* HT40 MCS0 */
	if (snr < 6)
		return 27000; /* HT40 MCS1 */
	if (snr < 10)
		return 40500; /* HT40 MCS2 */
	if (snr < 15)
		return 54000; /* HT40 MCS3 */
	if (snr < 17)
		return 81000; /* HT40 MCS4 */
	if (snr < 22)
		return 108000; /* HT40 MCS5 */
	if (snr < 24)
		return 121500; /* HT40 MCS6 */
	return 135000; /* HT40 MCS7 */
}