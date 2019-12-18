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
typedef  int u_char ;
struct snd_mixer {int dummy; } ;
struct ess_info {int dummy; } ;

/* Variables and functions */
#define  SOUND_MASK_CD 131 
#define  SOUND_MASK_IMIX 130 
#define  SOUND_MASK_LINE 129 
#define  SOUND_MASK_MIC 128 
 int /*<<< orphan*/  ess_setmixer (struct ess_info*,int,int) ; 
 struct ess_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static u_int32_t
essmix_setrecsrc(struct snd_mixer *m, u_int32_t src)
{
    	struct ess_info *sc = mix_getdevinfo(m);
    	u_char recdev;

    	switch (src) {
	case SOUND_MASK_CD:
		recdev = 0x02;
		break;

	case SOUND_MASK_LINE:
		recdev = 0x06;
		break;

	case SOUND_MASK_IMIX:
		recdev = 0x05;
		break;

	case SOUND_MASK_MIC:
	default:
		recdev = 0x00;
		src = SOUND_MASK_MIC;
		break;
	}

	ess_setmixer(sc, 0x1c, recdev);

	return src;
}