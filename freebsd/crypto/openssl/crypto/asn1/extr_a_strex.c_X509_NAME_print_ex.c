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
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int X509_NAME_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 unsigned long XN_FLAG_COMPAT ; 
 int do_name_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,unsigned long) ; 
 int /*<<< orphan*/  send_bio_chars ; 

int X509_NAME_print_ex(BIO *out, const X509_NAME *nm, int indent,
                       unsigned long flags)
{
    if (flags == XN_FLAG_COMPAT)
        return X509_NAME_print(out, nm, indent);
    return do_name_ex(send_bio_chars, out, nm, indent, flags);
}