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

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MLX5_ADAPTER_PAGE_SIZE ; 
 int MLX5_DEF_TOT_UUARS ; 
 int MLX5_MAX_BFREGS ; 
 int MLX5_NUM_NON_FP_BFREGS_PER_UAR ; 
 int align (int,int) ; 
 int atoi (char*) ; 
 char* getenv (char*) ; 
 int max (int,int) ; 

__attribute__((used)) static int get_total_uuars(int page_size)
{
	int size = MLX5_DEF_TOT_UUARS;
	int uuars_in_page;
	char *env;

	env = getenv("MLX5_TOTAL_UUARS");
	if (env)
		size = atoi(env);

	if (size < 1)
		return -EINVAL;

	uuars_in_page = page_size / MLX5_ADAPTER_PAGE_SIZE * MLX5_NUM_NON_FP_BFREGS_PER_UAR;
	size = max(uuars_in_page, size);
	size = align(size, MLX5_NUM_NON_FP_BFREGS_PER_UAR);
	if (size > MLX5_MAX_BFREGS)
		return -ENOMEM;

	return size;
}