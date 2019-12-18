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
struct snd_midi {int dummy; } ;
struct mpu401 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (struct mpu401*,int /*<<< orphan*/ ) ; 
 scalar_t__ MPU_ACK ; 
 int /*<<< orphan*/  MPU_RESET ; 
 int /*<<< orphan*/  MPU_UART ; 
 scalar_t__ READ (struct mpu401*) ; 
 scalar_t__ RXRDY (struct mpu401*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
mpu401_minit(struct snd_midi *sm, void *arg)
{
	struct mpu401 *m = arg;
	int i;

	CMD(m, MPU_RESET);
	CMD(m, MPU_UART);
	return 0;
	i = 0;
	while (++i < 2000) {
		if (RXRDY(m))
			if (READ(m) == MPU_ACK)
				break;
	}

	if (i < 2000) {
		CMD(m, MPU_UART);
		return 0;
	}
	printf("mpu401_minit failed active sensing\n");
	return 1;
}