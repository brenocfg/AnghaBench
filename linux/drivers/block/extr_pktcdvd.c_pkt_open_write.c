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
struct pktcdvd_device {int mmc3_profile; unsigned int write_speed; unsigned int read_speed; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  USE_WCACHING ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*,...) ; 
 int pkt_get_max_speed (struct pktcdvd_device*,unsigned int*) ; 
 int pkt_media_speed (struct pktcdvd_device*,unsigned int*) ; 
 int pkt_perform_opc (struct pktcdvd_device*) ; 
 int pkt_probe_settings (struct pktcdvd_device*) ; 
 int pkt_set_speed (struct pktcdvd_device*,unsigned int,unsigned int) ; 
 int pkt_set_write_settings (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  pkt_write_caching (struct pktcdvd_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkt_open_write(struct pktcdvd_device *pd)
{
	int ret;
	unsigned int write_speed, media_write_speed, read_speed;

	ret = pkt_probe_settings(pd);
	if (ret) {
		pkt_dbg(2, pd, "failed probe\n");
		return ret;
	}

	ret = pkt_set_write_settings(pd);
	if (ret) {
		pkt_dbg(1, pd, "failed saving write settings\n");
		return -EIO;
	}

	pkt_write_caching(pd, USE_WCACHING);

	ret = pkt_get_max_speed(pd, &write_speed);
	if (ret)
		write_speed = 16 * 177;
	switch (pd->mmc3_profile) {
		case 0x13: /* DVD-RW */
		case 0x1a: /* DVD+RW */
		case 0x12: /* DVD-RAM */
			pkt_dbg(1, pd, "write speed %ukB/s\n", write_speed);
			break;
		default:
			ret = pkt_media_speed(pd, &media_write_speed);
			if (ret)
				media_write_speed = 16;
			write_speed = min(write_speed, media_write_speed * 177);
			pkt_dbg(1, pd, "write speed %ux\n", write_speed / 176);
			break;
	}
	read_speed = write_speed;

	ret = pkt_set_speed(pd, write_speed, read_speed);
	if (ret) {
		pkt_dbg(1, pd, "couldn't set write speed\n");
		return -EIO;
	}
	pd->write_speed = write_speed;
	pd->read_speed = read_speed;

	ret = pkt_perform_opc(pd);
	if (ret) {
		pkt_dbg(1, pd, "Optimum Power Calibration failed\n");
	}

	return 0;
}