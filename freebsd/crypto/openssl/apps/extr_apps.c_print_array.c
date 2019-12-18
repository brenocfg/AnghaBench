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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 

void print_array(BIO *out, const char* title, int len, const unsigned char* d)
{
    int i;

    BIO_printf(out, "unsigned char %s[%d] = {", title, len);
    for (i = 0; i < len; i++) {
        if ((i % 10) == 0)
            BIO_printf(out, "\n    ");
        if (i < len - 1)
            BIO_printf(out, "0x%02X, ", d[i]);
        else
            BIO_printf(out, "0x%02X", d[i]);
    }
    BIO_printf(out, "\n};\n");
}