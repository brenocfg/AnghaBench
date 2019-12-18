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
struct data {unsigned int* data; size_t i; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fn(void *opaque)
{
  struct data *data = (struct data *)opaque;
  ZSTD_pthread_mutex_lock(&data->mutex);
  data->data[data->i] = (unsigned)(data->i);
  ++data->i;
  ZSTD_pthread_mutex_unlock(&data->mutex);
}