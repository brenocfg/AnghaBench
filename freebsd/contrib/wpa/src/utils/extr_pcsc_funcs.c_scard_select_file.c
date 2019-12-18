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
struct scard_data {int /*<<< orphan*/  sim_type; } ;

/* Variables and functions */
 int _scard_select_file (struct scard_data*,unsigned short,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scard_select_file(struct scard_data *scard, unsigned short file_id,
			     unsigned char *buf, size_t *buf_len)
{
	return _scard_select_file(scard, file_id, buf, buf_len,
				  scard->sim_type, NULL, 0);
}