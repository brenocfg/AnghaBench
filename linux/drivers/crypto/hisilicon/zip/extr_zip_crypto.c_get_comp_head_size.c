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
typedef  int u8 ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 size_t EINVAL ; 
#define  HZIP_ALG_TYPE_GZIP 129 
#define  HZIP_ALG_TYPE_ZLIB 128 
 size_t TO_HEAD_SIZE (int const) ; 
 size_t get_gzip_head_size (struct scatterlist*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static size_t get_comp_head_size(struct scatterlist *src, u8 req_type)
{
	switch (req_type) {
	case HZIP_ALG_TYPE_ZLIB:
		return TO_HEAD_SIZE(HZIP_ALG_TYPE_ZLIB);
	case HZIP_ALG_TYPE_GZIP:
		return get_gzip_head_size(src);
	default:
		pr_err("request type does not support!\n");
		return -EINVAL;
	}
}