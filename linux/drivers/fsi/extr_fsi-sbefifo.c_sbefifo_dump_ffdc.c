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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  __sbefifo_dump_ffdc (struct device*,int /*<<< orphan*/  const*,size_t,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbefifo_ffdc_mutex ; 

__attribute__((used)) static void sbefifo_dump_ffdc(struct device *dev, const __be32 *ffdc,
			      size_t ffdc_sz, bool internal)
{
	mutex_lock(&sbefifo_ffdc_mutex);
	__sbefifo_dump_ffdc(dev, ffdc, ffdc_sz, internal);
	mutex_unlock(&sbefifo_ffdc_mutex);
}