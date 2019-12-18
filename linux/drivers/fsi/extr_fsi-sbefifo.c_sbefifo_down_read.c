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
struct sbefifo {int /*<<< orphan*/  fsi_dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SBEFIFO_DOWN ; 
 int fsi_device_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sbefifo_down_read(struct sbefifo *sbefifo, __be32 *word)
{
	return fsi_device_read(sbefifo->fsi_dev, SBEFIFO_DOWN, word,
			       sizeof(*word));
}