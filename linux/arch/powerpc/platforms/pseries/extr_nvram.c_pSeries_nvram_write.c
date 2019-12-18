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
typedef  int ssize_t ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 unsigned long NVRW_CNT ; 
 scalar_t__ RTAS_UNKNOWN_SERVICE ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,unsigned long) ; 
 int /*<<< orphan*/  nvram_buf ; 
 int /*<<< orphan*/  nvram_lock ; 
 unsigned int nvram_size ; 
 scalar_t__ nvram_store ; 
 scalar_t__ rtas_call (scalar_t__,int,int,int*,unsigned int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t pSeries_nvram_write(char *buf, size_t count, loff_t *index)
{
	unsigned int i;
	unsigned long len;
	int done;
	unsigned long flags;
	const char *p = buf;

	if (nvram_size == 0 || nvram_store == RTAS_UNKNOWN_SERVICE)
		return -ENODEV;

	if (*index >= nvram_size)
		return 0;

	i = *index;
	if (i + count > nvram_size)
		count = nvram_size - i;

	spin_lock_irqsave(&nvram_lock, flags);

	for (; count != 0; count -= len) {
		len = count;
		if (len > NVRW_CNT)
			len = NVRW_CNT;

		memcpy(nvram_buf, p, len);

		if ((rtas_call(nvram_store, 3, 2, &done, i, __pa(nvram_buf),
			       len) != 0) || len != done) {
			spin_unlock_irqrestore(&nvram_lock, flags);
			return -EIO;
		}
		
		p += len;
		i += len;
	}
	spin_unlock_irqrestore(&nvram_lock, flags);
	
	*index = i;
	return p - buf;
}