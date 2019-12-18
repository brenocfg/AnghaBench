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
typedef  int u_char ;

/* Variables and functions */
#define  ET_MEDIA_12FDD 132 
#define  ET_MEDIA_144FDD 131 
#define  ET_MEDIA_288FDD 130 
#define  ET_MEDIA_HDD 129 
#define  ET_MEDIA_NOEM 128 

const char *
media_type_string(u_char media_type)
{

	switch (media_type) {
	case ET_MEDIA_NOEM:
		return ("no emulation");
	case ET_MEDIA_12FDD:
		return ("1.2MB FDD");
	case ET_MEDIA_144FDD:
		return ("1.44MB FDD");
	case ET_MEDIA_288FDD:
		return ("2.88MB FDD");
	case ET_MEDIA_HDD:
		return ("HDD");
	default:
		return ("invalid");
	}
}