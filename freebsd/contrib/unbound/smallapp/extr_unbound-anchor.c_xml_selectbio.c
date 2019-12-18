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
struct xml_data {int /*<<< orphan*/ * cdigest; int /*<<< orphan*/ * cdigtype; int /*<<< orphan*/ * calgo; int /*<<< orphan*/ * ctag; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static BIO*
xml_selectbio(struct xml_data* data, const char* tag)
{
	BIO* b = NULL;
	if(strcasecmp(tag, "KeyTag") == 0)
		b = data->ctag;
	else if(strcasecmp(tag, "Algorithm") == 0)
		b = data->calgo;
	else if(strcasecmp(tag, "DigestType") == 0)
		b = data->cdigtype;
	else if(strcasecmp(tag, "Digest") == 0)
		b = data->cdigest;
	return b;
}