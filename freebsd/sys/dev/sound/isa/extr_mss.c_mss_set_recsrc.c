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
struct mss_info {int dummy; } ;

/* Variables and functions */
#define  SOUND_MASK_CD 133 
#define  SOUND_MASK_IMIX 132 
#define  SOUND_MASK_LINE 131 
#define  SOUND_MASK_LINE1 130 
#define  SOUND_MASK_LINE3 129 
#define  SOUND_MASK_MIC 128 
 int ad_read (struct mss_info*,int) ; 
 int /*<<< orphan*/  ad_write (struct mss_info*,int,int) ; 

__attribute__((used)) static int
mss_set_recsrc(struct mss_info *mss, int mask)
{
    	u_char   recdev;

    	switch (mask) {
    	case SOUND_MASK_LINE:
    	case SOUND_MASK_LINE3:
		recdev = 0;
		break;

    	case SOUND_MASK_CD:
    	case SOUND_MASK_LINE1:
		recdev = 0x40;
		break;

    	case SOUND_MASK_IMIX:
		recdev = 0xc0;
		break;

    	case SOUND_MASK_MIC:
    	default:
		mask = SOUND_MASK_MIC;
		recdev = 0x80;
    	}
    	ad_write(mss, 0, (ad_read(mss, 0) & 0x3f) | recdev);
    	ad_write(mss, 1, (ad_read(mss, 1) & 0x3f) | recdev);
    	return mask;
}