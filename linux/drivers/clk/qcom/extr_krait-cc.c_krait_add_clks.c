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
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct clk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int krait_add_div (struct device*,int,char const*,unsigned int) ; 
 struct clk* krait_add_pri_mux (struct device*,int,char const*,unsigned int) ; 
 int krait_add_sec_mux (struct device*,int,char const*,unsigned int,int) ; 

__attribute__((used)) static struct clk *krait_add_clks(struct device *dev, int id, bool unique_aux)
{
	int ret;
	unsigned int offset;
	void *p = NULL;
	const char *s;
	struct clk *clk;

	if (id >= 0) {
		offset = 0x4501 + (0x1000 * id);
		s = p = kasprintf(GFP_KERNEL, "%d", id);
		if (!s)
			return ERR_PTR(-ENOMEM);
	} else {
		offset = 0x500;
		s = "_l2";
	}

	ret = krait_add_div(dev, id, s, offset);
	if (ret) {
		clk = ERR_PTR(ret);
		goto err;
	}

	ret = krait_add_sec_mux(dev, id, s, offset, unique_aux);
	if (ret) {
		clk = ERR_PTR(ret);
		goto err;
	}

	clk = krait_add_pri_mux(dev, id, s, offset);
err:
	kfree(p);
	return clk;
}