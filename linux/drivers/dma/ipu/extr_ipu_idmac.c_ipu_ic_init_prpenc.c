#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  out_pixel_fmt; int /*<<< orphan*/  in_pixel_fmt; int /*<<< orphan*/  out_width; int /*<<< orphan*/  in_width; int /*<<< orphan*/  out_height; int /*<<< orphan*/  in_height; } ;
union ipu_channel_param {TYPE_1__ video; } ;
typedef  int uint32_t ;
struct ipu {int /*<<< orphan*/  dev; } ;
typedef  enum ipu_color_space { ____Placeholder_ipu_color_space } ipu_color_space ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IC_CONF ; 
 int IC_CONF_RWS_EN ; 
 int /*<<< orphan*/  IC_PRP_ENC_RSC ; 
 int /*<<< orphan*/  calc_resize_coeffs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int format_to_colorspace (int /*<<< orphan*/ ) ; 
 int idmac_read_icreg (struct ipu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmac_write_icreg (struct ipu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipu_ic_init_prpenc(struct ipu *ipu,
			      union ipu_channel_param *params, bool src_is_csi)
{
	uint32_t reg, ic_conf;
	uint32_t downsize_coeff, resize_coeff;
	enum ipu_color_space in_fmt, out_fmt;

	/* Setup vertical resizing */
	calc_resize_coeffs(params->video.in_height,
			    params->video.out_height,
			    &resize_coeff, &downsize_coeff);
	reg = (downsize_coeff << 30) | (resize_coeff << 16);

	/* Setup horizontal resizing */
	calc_resize_coeffs(params->video.in_width,
			    params->video.out_width,
			    &resize_coeff, &downsize_coeff);
	reg |= (downsize_coeff << 14) | resize_coeff;

	/* Setup color space conversion */
	in_fmt = format_to_colorspace(params->video.in_pixel_fmt);
	out_fmt = format_to_colorspace(params->video.out_pixel_fmt);

	/*
	 * Colourspace conversion unsupported yet - see _init_csc() in
	 * Freescale sources
	 */
	if (in_fmt != out_fmt) {
		dev_err(ipu->dev, "Colourspace conversion unsupported!\n");
		return -EOPNOTSUPP;
	}

	idmac_write_icreg(ipu, reg, IC_PRP_ENC_RSC);

	ic_conf = idmac_read_icreg(ipu, IC_CONF);

	if (src_is_csi)
		ic_conf &= ~IC_CONF_RWS_EN;
	else
		ic_conf |= IC_CONF_RWS_EN;

	idmac_write_icreg(ipu, ic_conf, IC_CONF);

	return 0;
}