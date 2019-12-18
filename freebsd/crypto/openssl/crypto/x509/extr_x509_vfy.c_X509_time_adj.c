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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/ * X509_time_adj_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *) ; 

ASN1_TIME *X509_time_adj(ASN1_TIME *s, long offset_sec, time_t *in_tm)
{
    return X509_time_adj_ex(s, 0, offset_sec, in_tm);
}