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
typedef  int u_int32_t ;
struct snd_mixer {int dummy; } ;
struct ad1816_info {int dummy; } ;

/* Variables and functions */
#define  SOUND_MASK_CD 132 
#define  SOUND_MASK_LINE 131 
#define  SOUND_MASK_LINE1 130 
#define  SOUND_MASK_LINE3 129 
#define  SOUND_MASK_MIC 128 
 int /*<<< orphan*/  ad1816_lock (struct ad1816_info*) ; 
 int ad1816_read (struct ad1816_info*,int) ; 
 int /*<<< orphan*/  ad1816_unlock (struct ad1816_info*) ; 
 int /*<<< orphan*/  ad1816_write (struct ad1816_info*,int,int) ; 
 struct ad1816_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static u_int32_t
ad1816mix_setrecsrc(struct snd_mixer *m, u_int32_t src)
{
	struct ad1816_info *ad1816 = mix_getdevinfo(m);
    	int dev;

    	switch (src) {
    	case SOUND_MASK_LINE:
    	case SOUND_MASK_LINE3:
		dev = 0x00;
		break;

    	case SOUND_MASK_CD:
    	case SOUND_MASK_LINE1:
		dev = 0x20;
		break;

    	case SOUND_MASK_MIC:
    	default:
		dev = 0x50;
		src = SOUND_MASK_MIC;
    	}

    	dev |= dev << 8;
	ad1816_lock(ad1816);
    	ad1816_write(ad1816, 20, (ad1816_read(ad1816, 20) & ~0x7070) | dev);
	ad1816_unlock(ad1816);
    	return src;
}