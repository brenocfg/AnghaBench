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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ urtw_isbmode (int) ; 
 int urtw_rate2dbps (int) ; 

__attribute__((used)) static int
urtw_compute_txtime(uint16_t framelen, uint16_t rate,
    uint8_t ismgt, uint8_t isshort)
{
	uint16_t     ceiling, frametime, n_dbps;

	if (urtw_isbmode(rate)) {
		if (ismgt || !isshort || rate == 2)
			frametime = (uint16_t)(144 + 48 +
			    (framelen * 8 / (rate / 2)));
		else
			frametime = (uint16_t)(72 + 24 +
			    (framelen * 8 / (rate / 2)));
		if ((framelen * 8 % (rate / 2)) != 0)
			frametime++;
	} else {
		n_dbps = urtw_rate2dbps(rate);
		ceiling = (16 + 8 * framelen + 6) / n_dbps
		    + (((16 + 8 * framelen + 6) % n_dbps) ? 1 : 0);
		frametime = (uint16_t)(16 + 4 + 4 * ceiling + 6);
	}
	return (frametime);
}