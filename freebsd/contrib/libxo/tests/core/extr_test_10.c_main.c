#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* member_0; char* member_1; char* member_2; } ;
typedef  TYPE_1__ xo_info_t ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_COLOR ; 
 int /*<<< orphan*/  XOF_INFO ; 
 int /*<<< orphan*/  XOF_KEYS ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 int /*<<< orphan*/  XOF_XPATH ; 
 int /*<<< orphan*/  XO_STYLE_HTML ; 
 int /*<<< orphan*/  XO_STYLE_JSON ; 
 int /*<<< orphan*/  XO_STYLE_TEXT ; 
 int /*<<< orphan*/  XO_STYLE_XML ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  xo_attr (char*,char*) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_container_h (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_container_h (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_set_info (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  xo_set_style (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_set_version (char*) ; 
 scalar_t__ xo_streq (char*,char*) ; 

int
main (int argc, char **argv)
{
    static char base_grocery[] = "GRO";
    static char base_hardware[] = "HRD";
    struct item {
	const char *i_title;
	int i_sold;
	int i_instock;
	int i_onorder;
	const char *i_sku_base;
	int i_sku_num;
    };
    struct item list[] = {
	{ "gum", 1412, 54, 10, base_grocery, 415 },
	{ "rope", 85, 4, 2, base_hardware, 212 },
	{ "ladder", 0, 2, 1, base_hardware, 517 },
	{ "bolt", 4123, 144, 42, base_hardware, 632 },
	{ "water", 17, 14, 2, base_grocery, 2331 },
	{ NULL, 0, 0, 0, NULL, 0 }
    };
    struct item list2[] = {
	{ "fish", 1321, 45, 1, base_grocery, 533 },
	{ NULL, 0, 0, 0, NULL, 0 }
    };
    struct item *ip;
    xo_info_t info[] = {
	{ "in-stock", "number", "Number of items in stock" },
	{ "name", "string", "Name of the item" },
	{ "on-order", "number", "Number of items on order" },
	{ "sku", "string", "Stock Keeping Unit" },
	{ "sold", "number", "Number of items sold" },
	{ NULL, NULL, NULL },
    };
    int info_count = (sizeof(info) / sizeof(info[0])) - 1;
    
    argc = xo_parse_args(argc, argv);
    if (argc < 0)
	return 1;

    for (argc = 1; argv[argc]; argc++) {
	if (xo_streq(argv[argc], "xml"))
	    xo_set_style(NULL, XO_STYLE_XML);
	else if (xo_streq(argv[argc], "json"))
	    xo_set_style(NULL, XO_STYLE_JSON);
	else if (xo_streq(argv[argc], "text"))
	    xo_set_style(NULL, XO_STYLE_TEXT);
	else if (xo_streq(argv[argc], "html"))
	    xo_set_style(NULL, XO_STYLE_HTML);
	else if (xo_streq(argv[argc], "pretty"))
	    xo_set_flags(NULL, XOF_PRETTY);
	else if (xo_streq(argv[argc], "xpath"))
	    xo_set_flags(NULL, XOF_XPATH);
	else if (xo_streq(argv[argc], "info"))
	    xo_set_flags(NULL, XOF_INFO);
        else if (xo_streq(argv[argc], "error")) {
            close(-1);
            xo_err(1, "error detected");
        }
    }

    xo_set_info(NULL, info, info_count);
    xo_set_flags(NULL, XOF_KEYS);

    /*  Normally one would use "XOF_COLOR_ALLOWED", but we want to force it */
    xo_set_flags(NULL, XOF_COLOR);

    xo_set_version("3.1.4");

    xo_open_container_h(NULL, "top");

    xo_attr("test", "value");
    xo_open_container("data");
    xo_open_list("item");
    xo_attr("test2", "value2");

    static const char *colors[] =
	{ "blue", "green", "red", "yellow", "default", NULL };

    int i;
    for (i = 0; colors[i]; i++) {
	if (i > 0)
	    xo_emit("{C:/bg-%s}", colors[i-1]);
	xo_emit("{C:/fg-%s}{T:/%s}", colors[i], colors[i]);
    }
    xo_emit("{C:reset}\n");

    xo_emit("{C:bold}{:data} {C:underline}{:data} {C:inverse}{:data} "
	    "{C:no-bold}{:data} {C:no-inverse}{:data} "
	    "{C:no-underline}{:data}\n",
	    "bold", "bold-ul", "triple", "inv-ul", "underline", "plain");

    xo_emit("{T:Item/%-10s}{C:bold,underline}{T:Total Sold/%12s}{C:no-bold}"
	    "{T:In Stock/%12s}{C:/%s}"
	    "{T:On Order/%12s}{C:normal}{T:SKU/%5s}\n", "inverse");

#if 0
    xo_finish();
    return 0;
#endif

    for (ip = list; ip->i_title; ip++) {
	xo_open_instance("item");
	xo_attr("test3", "value3");

	xo_emit("{keq:sku/%s-%u/%s-000-%u}"
		"{k:name/%-10s/%s}{n:sold/%12u/%u}"
		"{C:/%s}{:in-stock/%12u/%u}{C:normal}"
		"{C:/fg-%s}{:on-order/%12u/%u}{C:/fg-default}"
		"{qkd:sku/%5s-000-%u/%s-000-%u}\n",
		ip->i_sku_base, ip->i_sku_num,
		ip->i_title, ip->i_sold,
		(ip->i_instock < 5) ? "inverse" : "normal", ip->i_instock,
		(ip->i_onorder > 5) ? "yellow" : "default", ip->i_onorder,
		ip->i_sku_base, ip->i_sku_num);

	xo_close_instance("item");
    }

    xo_close_list("item");
    xo_close_container("data");

    xo_emit("\n\n");

    xo_open_container("data");
    xo_open_list("item");

    for (ip = list; ip->i_title; ip++) {
	xo_open_instance("item");

	xo_emit("{keq:sku/%s-%u/%s-000-%u}", ip->i_sku_base, ip->i_sku_num);
	xo_emit("{L:Item} '{k:name/%s}':\n", ip->i_title);
	xo_emit("{P:   }{L:Total sold}: {n:sold/%u%s}\n",
		ip->i_sold, ip->i_sold ? ".0" : "");
	xo_emit("{P:   }{Lcw:In stock}{C:inverse}{:in-stock/%u}{C:}\n",
		ip->i_instock);
	xo_emit("{P:   }{Lcw:On order}{:on-order/%u}\n", ip->i_onorder);
	xo_emit("{P:   }{L:SKU}: {qkd:sku/%s-000-%u}\n",
		ip->i_sku_base, ip->i_sku_num);

	xo_close_instance("item");
    }

    xo_close_list("item");
    xo_close_container("data");

    xo_open_container("data");
    xo_open_list("item");

    for (ip = list2; ip->i_title; ip++) {
	xo_open_instance("item");

	xo_emit("{keq:sku/%s-%u/%s-000-%u}", ip->i_sku_base, ip->i_sku_num);
	xo_emit("{L:Item} '{k:name/%s}':\n", ip->i_title);
	xo_emit("{P:   }{C:bg-blue   , fg-white, bold   }{L:Total sold}: "
		"{n:sold/%u%s}{C:}\n",
		ip->i_sold, ip->i_sold ? ".0" : "");
	xo_emit("{P:   }{Lcw:In stock}{:in-stock/%u}\n", ip->i_instock);
	xo_emit("{P:   }{Lcw:On order}{:on-order/%u}\n", ip->i_onorder);
	xo_emit("{P:   }{L:SKU}: {qkd:sku/%s-000-%u}\n",
		ip->i_sku_base, ip->i_sku_num);

	xo_close_instance("item");
    }

    xo_close_list("item");
    xo_close_container("data");

    xo_open_container("data");
    xo_open_list("item");

    for (ip = list; ip->i_title; ip++) {
	xo_attr("test4", "value4");
	xo_emit("{Lwc:Item}{l:item}\n", ip->i_title);
    }

    xo_close_list("item");
    xo_close_container("data");

    xo_emit("X{P:}X", "epic fail");
    xo_emit("X{T:}X", "epic fail");
    xo_emit("X{N:}X", "epic fail");
    xo_emit("X{L:}X\n", "epic fail");

    xo_emit("X{P:        }X{Lwc:Cost}{:cost/%u}\n", 425);
    xo_emit("X{P:/%30s}X{Lwc:Cost}{:cost/%u}\n", "", 455);

    xo_close_container_h(NULL, "top");

    xo_finish();

    return 0;
}