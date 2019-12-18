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
struct xz_dec {int dummy; } ;
struct xz_buf {int dummy; } ;
typedef  enum xz_ret { ____Placeholder_xz_ret } xz_ret ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  XZ_DATA_ERROR 134 
#define  XZ_FORMAT_ERROR 133 
#define  XZ_MEMLIMIT_ERROR 132 
#define  XZ_MEM_ERROR 131 
#define  XZ_OK 130 
#define  XZ_OPTIONS_ERROR 129 
#define  XZ_STREAM_END 128 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int xz_dec_run (struct xz_dec*,struct xz_buf*) ; 

__attribute__((used)) static int mlxfw_mfa2_xz_dec_run(struct xz_dec *xz_dec, struct xz_buf *xz_buf,
				 bool *finished)
{
	enum xz_ret xz_ret;

	xz_ret = xz_dec_run(xz_dec, xz_buf);

	switch (xz_ret) {
	case XZ_STREAM_END:
		*finished = true;
		return 0;
	case XZ_OK:
		*finished = false;
		return 0;
	case XZ_MEM_ERROR:
		pr_err("xz no memory\n");
		return -ENOMEM;
	case XZ_DATA_ERROR:
		pr_err("xz file corrupted\n");
		return -EINVAL;
	case XZ_FORMAT_ERROR:
		pr_err("xz format not found\n");
		return -EINVAL;
	case XZ_OPTIONS_ERROR:
		pr_err("unsupported xz option\n");
		return -EINVAL;
	case XZ_MEMLIMIT_ERROR:
		pr_err("xz dictionary too small\n");
		return -EINVAL;
	default:
		pr_err("xz error %d\n", xz_ret);
		return -EINVAL;
	}
}