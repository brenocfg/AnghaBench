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
typedef  scalar_t__ u_int ;
struct coredump_params {int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_BUF_SIZE ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,scalar_t__) ; 
 int compressor_write (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int copyin (char*,char*,scalar_t__) ; 

__attribute__((used)) static int
compress_chunk(struct coredump_params *p, char *base, char *buf, u_int len)
{
	u_int chunk_len;
	int error;

	while (len > 0) {
		chunk_len = MIN(len, CORE_BUF_SIZE);

		/*
		 * We can get EFAULT error here.
		 * In that case zero out the current chunk of the segment.
		 */
		error = copyin(base, buf, chunk_len);
		if (error != 0)
			bzero(buf, chunk_len);
		error = compressor_write(p->comp, buf, chunk_len);
		if (error != 0)
			break;
		base += chunk_len;
		len -= chunk_len;
	}
	return (error);
}