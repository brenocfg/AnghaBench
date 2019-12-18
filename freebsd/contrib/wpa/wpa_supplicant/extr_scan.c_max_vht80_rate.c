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

__attribute__((used)) static unsigned int max_vht80_rate(int snr)
{
	if (snr < 1)
		return 0;
	if (snr < 2)
		return 29300; /* VHT80 MCS0 */
	if (snr < 5)
		return 58500; /* VHT80 MCS1 */
	if (snr < 9)
		return 87800; /* VHT80 MCS2 */
	if (snr < 11)
		return 117000; /* VHT80 MCS3 */
	if (snr < 15)
		return 175500; /* VHT80 MCS4 */
	if (snr < 16)
		return 234000; /* VHT80 MCS5 */
	if (snr < 18)
		return 263300; /* VHT80 MCS6 */
	if (snr < 20)
		return 292500; /* VHT80 MCS7 */
	if (snr < 22)
		return 351000; /* VHT80 MCS8 */
	return 390000; /* VHT80 MCS9 */
}