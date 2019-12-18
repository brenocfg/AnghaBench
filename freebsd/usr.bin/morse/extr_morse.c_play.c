#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int duration; void* frequency; } ;

/* Variables and functions */
 void* CHAR_SPACE ; 
 void* DASH_LEN ; 
 int /*<<< orphan*/  SPKRTONE ; 
 void* WORD_SPACE ; 
 void* cdot_clock ; 
 void* dot_clock ; 
 int /*<<< orphan*/  err (int,char*) ; 
 void* freq ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ sound ; 
 int /*<<< orphan*/  spkr ; 

__attribute__((used)) static void
play(const char *s)
{
#ifdef SPEAKER
	const char *c;

	for (c = s; *c != '\0'; c++) {
		switch (*c) {
		case '.':
			sound.frequency = freq;
			sound.duration = dot_clock;
			break;
		case '-':
			sound.frequency = freq;
			sound.duration = dot_clock * DASH_LEN;
			break;
		case ' ':
			sound.frequency = 0;
			sound.duration = cdot_clock * WORD_SPACE;
			break;
		default:
			sound.duration = 0;
		}
		if (sound.duration) {
			if (ioctl(spkr, SPKRTONE, &sound) == -1) {
				err(1, "ioctl play");
			}
		}
		sound.frequency = 0;
		sound.duration = dot_clock;
		if (ioctl(spkr, SPKRTONE, &sound) == -1) {
			err(1, "ioctl rest");
		}
	}
	sound.frequency = 0;
	sound.duration = cdot_clock * CHAR_SPACE;
	ioctl(spkr, SPKRTONE, &sound);
#endif
}