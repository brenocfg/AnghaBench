#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  oppanel_line_t ;
struct TYPE_9__ {void* line; void* line_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __pa (TYPE_2__*) ; 
 void* cpu_to_be64 (int) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int num_lines ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 TYPE_2__* oppanel_data ; 
 int /*<<< orphan*/  oppanel_dev ; 
 TYPE_2__* oppanel_lines ; 
 int oppanel_size ; 
 int /*<<< orphan*/  pr_devel (char*,int,int,int) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*) ; 

__attribute__((used)) static int oppanel_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	u32 line_len;
	int rc, i;

	rc = of_property_read_u32(np, "#length", &line_len);
	if (rc) {
		pr_err_ratelimited("Operator panel length property not found\n");
		return rc;
	}
	rc = of_property_read_u32(np, "#lines", &num_lines);
	if (rc) {
		pr_err_ratelimited("Operator panel lines property not found\n");
		return rc;
	}
	oppanel_size = line_len * num_lines;

	pr_devel("Operator panel of size %u found with %u lines of length %u\n",
			oppanel_size, num_lines, line_len);

	oppanel_data = kcalloc(oppanel_size, sizeof(*oppanel_data), GFP_KERNEL);
	if (!oppanel_data)
		return -ENOMEM;

	oppanel_lines = kcalloc(num_lines, sizeof(oppanel_line_t), GFP_KERNEL);
	if (!oppanel_lines) {
		rc = -ENOMEM;
		goto free_oppanel_data;
	}

	memset(oppanel_data, ' ', oppanel_size);
	for (i = 0; i < num_lines; i++) {
		oppanel_lines[i].line_len = cpu_to_be64(line_len);
		oppanel_lines[i].line = cpu_to_be64(__pa(&oppanel_data[i *
						line_len]));
	}

	rc = misc_register(&oppanel_dev);
	if (rc) {
		pr_err_ratelimited("Failed to register as misc device\n");
		goto free_oppanel;
	}

	return 0;

free_oppanel:
	kfree(oppanel_lines);
free_oppanel_data:
	kfree(oppanel_data);
	return rc;
}