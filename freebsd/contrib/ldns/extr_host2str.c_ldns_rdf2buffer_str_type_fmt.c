#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_output_format ;
typedef  int /*<<< orphan*/  ldns_buffer ;
struct TYPE_2__ {scalar_t__ _name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_output_format_covers_type (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_read_uint16 (int /*<<< orphan*/ ) ; 
 TYPE_1__* ldns_rr_descript (scalar_t__) ; 

__attribute__((used)) static ldns_status
ldns_rdf2buffer_str_type_fmt(ldns_buffer *output,
		const ldns_output_format* fmt, const ldns_rdf *rdf)
{
        uint16_t data = ldns_read_uint16(ldns_rdf_data(rdf));

	if (! ldns_output_format_covers_type(fmt, data) &&
			ldns_rr_descript(data) &&
			ldns_rr_descript(data)->_name) {

		ldns_buffer_printf(output, "%s",ldns_rr_descript(data)->_name);
	} else {
		ldns_buffer_printf(output, "TYPE%u", data);
	}
	return  ldns_buffer_status(output);
}