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
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int HZIP_GZIP_HEAD_BUF ; 
 size_t __get_gzip_head_size (char*) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (struct scatterlist*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sg_nents (struct scatterlist*) ; 

__attribute__((used)) static size_t get_gzip_head_size(struct scatterlist *sgl)
{
	char buf[HZIP_GZIP_HEAD_BUF];

	sg_copy_to_buffer(sgl, sg_nents(sgl), buf, sizeof(buf));

	return __get_gzip_head_size(buf);
}