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

int BIO_hex_string(BIO *out, int indent, int width, unsigned char *data,
                   int datalen)
{
    int i, j = 0;

    if (datalen < 1)
        return 1;

    for (i = 0; i < datalen - 1; i++) {
        if (i && !j)
            BIO_printf(out, "%*s", indent, "");

        BIO_printf(out, "%02X:", data[i]);

        j = (j + 1) % width;
        if (!j)
            BIO_printf(out, "\n");
    }

    if (i && !j)
        BIO_printf(out, "%*s", indent, "");
    BIO_printf(out, "%02X", data[datalen - 1]);
    return 1;
}