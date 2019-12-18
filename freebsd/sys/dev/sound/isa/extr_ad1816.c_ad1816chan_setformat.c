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
struct ad1816_info {int dummy; } ;
struct ad1816_chinfo {scalar_t__ dir; struct ad1816_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AD1816_ALAW ; 
 int AD1816_CAPT ; 
 int AD1816_MULAW ; 
 int AD1816_PLAY ; 
 int AD1816_S16BE ; 
 int AD1816_S16LE ; 
 int AD1816_STEREO ; 
 int AD1816_U8 ; 
#define  AFMT_A_LAW 132 
 int AFMT_CHANNEL (int) ; 
 int AFMT_ENCODING (int) ; 
#define  AFMT_MU_LAW 131 
#define  AFMT_S16_BE 130 
#define  AFMT_S16_LE 129 
#define  AFMT_U8 128 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  ad1816_lock (struct ad1816_info*) ; 
 int /*<<< orphan*/  ad1816_unlock (struct ad1816_info*) ; 
 int /*<<< orphan*/  ad1816_write (struct ad1816_info*,int,int) ; 
 int /*<<< orphan*/  io_wr (struct ad1816_info*,int,int) ; 

__attribute__((used)) static int
ad1816chan_setformat(kobj_t obj, void *data, u_int32_t format)
{
	struct ad1816_chinfo *ch = data;
  	struct ad1816_info *ad1816 = ch->parent;
    	int fmt = AD1816_U8, reg;

	ad1816_lock(ad1816);
    	if (ch->dir == PCMDIR_PLAY) {
        	reg = AD1816_PLAY;
        	ad1816_write(ad1816, 8, 0x0000);	/* reset base and current counter */
        	ad1816_write(ad1816, 9, 0x0000);	/* for playback and capture */
    	} else {
        	reg = AD1816_CAPT;
        	ad1816_write(ad1816, 10, 0x0000);
        	ad1816_write(ad1816, 11, 0x0000);
    	}
    	switch (AFMT_ENCODING(format)) {
    	case AFMT_A_LAW:
        	fmt = AD1816_ALAW;
		break;

    	case AFMT_MU_LAW:
		fmt = AD1816_MULAW;
		break;

    	case AFMT_S16_LE:
		fmt = AD1816_S16LE;
		break;

    	case AFMT_S16_BE:
		fmt = AD1816_S16BE;
		break;

    	case AFMT_U8:
		fmt = AD1816_U8;
		break;
    	}
    	if (AFMT_CHANNEL(format) > 1) fmt |= AD1816_STEREO;
    	io_wr(ad1816, reg, fmt);
	ad1816_unlock(ad1816);
#if 0
    	return format;
#else
    	return 0;
#endif
}