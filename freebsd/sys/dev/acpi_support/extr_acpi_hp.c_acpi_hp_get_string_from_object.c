#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Length; int /*<<< orphan*/  Pointer; } ;
struct TYPE_5__ {scalar_t__ Type; TYPE_1__ String; } ;
typedef  TYPE_2__ ACPI_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  acpi_hp_hex_decode (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline char*
acpi_hp_get_string_from_object(ACPI_OBJECT* obj, char* dst, size_t size) {
	int	length;

	dst[0] = 0;
	if (obj->Type == ACPI_TYPE_STRING) {
		length = obj->String.Length+1;
		if (length > size) {
			length = size - 1;
		}
		strlcpy(dst, obj->String.Pointer, length);
		acpi_hp_hex_decode(dst);
	}

	return (dst);
}