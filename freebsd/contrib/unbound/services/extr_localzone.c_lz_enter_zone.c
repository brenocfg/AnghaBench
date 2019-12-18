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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct local_zones {int dummy; } ;
struct local_zone {int dummy; } ;
typedef  enum localzone_type { ____Placeholder_localzone_type } localzone_type ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_zone_str2type (char const*,int*) ; 
 int /*<<< orphan*/  log_err (char*,char const*,char const*) ; 
 struct local_zone* lz_enter_zone_dname (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_dname (char const*,int /*<<< orphan*/ **,size_t*,int*) ; 

__attribute__((used)) static struct local_zone*
lz_enter_zone(struct local_zones* zones, const char* name, const char* type,
	uint16_t dclass)
{
	struct local_zone* z;
	enum localzone_type t;
	uint8_t* nm;
	size_t len;
	int labs;
	if(!parse_dname(name, &nm, &len, &labs)) {
		log_err("bad zone name %s %s", name, type);
		return NULL;
	}
	if(!local_zone_str2type(type, &t)) {
		log_err("bad lz_enter_zone type %s %s", name, type);
		free(nm);
		return NULL;
	}
	if(!(z=lz_enter_zone_dname(zones, nm, len, labs, t, dclass))) {
		log_err("could not enter zone %s %s", name, type);
		return NULL;
	}
	return z;
}