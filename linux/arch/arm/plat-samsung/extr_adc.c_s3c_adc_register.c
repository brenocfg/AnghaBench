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
struct s3c_adc_client {unsigned int is_ts; void (* select_cb ) (struct s3c_adc_client*,unsigned int) ;void (* convert_cb ) (struct s3c_adc_client*,unsigned int,unsigned int,unsigned int*) ;struct platform_device* pdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct s3c_adc_client* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct s3c_adc_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 void s3c_adc_default_select (struct s3c_adc_client*,unsigned int) ; 

struct s3c_adc_client *s3c_adc_register(struct platform_device *pdev,
					void (*select)(struct s3c_adc_client *client,
						       unsigned int selected),
					void (*conv)(struct s3c_adc_client *client,
						     unsigned d0, unsigned d1,
						     unsigned *samples_left),
					unsigned int is_ts)
{
	struct s3c_adc_client *client;

	WARN_ON(!pdev);

	if (!select)
		select = s3c_adc_default_select;

	if (!pdev)
		return ERR_PTR(-EINVAL);

	client = kzalloc(sizeof(*client), GFP_KERNEL);
	if (!client)
		return ERR_PTR(-ENOMEM);

	client->pdev = pdev;
	client->is_ts = is_ts;
	client->select_cb = select;
	client->convert_cb = conv;

	return client;
}