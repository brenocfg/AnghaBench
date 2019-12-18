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
struct xml_data {int /*<<< orphan*/  num_keys; int /*<<< orphan*/  ds; int /*<<< orphan*/  cdigest; int /*<<< orphan*/  cdigtype; int /*<<< orphan*/  calgo; int /*<<< orphan*/  ctag; } ;

/* Variables and functions */
 int /*<<< orphan*/  xml_append_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_append_str (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
xml_append_ds(struct xml_data* data)
{
	/* write DS to accumulated DS */
	xml_append_str(data->ds, ". IN DS ");
	xml_append_bio(data->ds, data->ctag);
	xml_append_str(data->ds, " ");
	xml_append_bio(data->ds, data->calgo);
	xml_append_str(data->ds, " ");
	xml_append_bio(data->ds, data->cdigtype);
	xml_append_str(data->ds, " ");
	xml_append_bio(data->ds, data->cdigest);
	xml_append_str(data->ds, "\n");
	data->num_keys++;
}