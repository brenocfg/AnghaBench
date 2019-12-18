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

/* Variables and functions */
 unsigned long X509_NAME_hash (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long xname_hash(const X509_NAME *a)
{
    return X509_NAME_hash((X509_NAME *)a);
}