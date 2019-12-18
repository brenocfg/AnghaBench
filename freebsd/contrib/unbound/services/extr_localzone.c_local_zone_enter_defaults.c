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
struct local_zones {int dummy; } ;
struct local_zone {int /*<<< orphan*/  lock; } ;
struct config_file {int /*<<< orphan*/  unblock_lan_zones; scalar_t__ local_zones_disable_default; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  add_empty_default (struct local_zones*,struct config_file*,char const*) ; 
 char** as112_zones ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  lz_enter_rr_into_zone (struct local_zone*,char*) ; 
 struct local_zone* lz_enter_zone (struct local_zones*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lz_exists (struct local_zones*,char*) ; 
 int /*<<< orphan*/  lz_nodefault (struct config_file*,char*) ; 

int local_zone_enter_defaults(struct local_zones* zones, struct config_file* cfg)
{
	struct local_zone* z;
	const char** zstr;

	/* Do not add any default */
	if(cfg->local_zones_disable_default)
		return 1;

	/* this list of zones is from RFC 6303 and RFC 7686 */

	/* block localhost level zones first, then onion and later the LAN zones */

	/* localhost. zone */
	if(!lz_exists(zones, "localhost.") &&
		!lz_nodefault(cfg, "localhost.")) {
		if(!(z=lz_enter_zone(zones, "localhost.", "redirect", 
			LDNS_RR_CLASS_IN)) ||
		   !lz_enter_rr_into_zone(z,
			"localhost. 10800 IN NS localhost.") ||
		   !lz_enter_rr_into_zone(z,
			"localhost. 10800 IN SOA localhost. nobody.invalid. "
			"1 3600 1200 604800 10800") ||
		   !lz_enter_rr_into_zone(z,
			"localhost. 10800 IN A 127.0.0.1") ||
		   !lz_enter_rr_into_zone(z,
			"localhost. 10800 IN AAAA ::1")) {
			log_err("out of memory adding default zone");
			if(z) { lock_rw_unlock(&z->lock); }
			return 0;
		}
		lock_rw_unlock(&z->lock);
	}
	/* reverse ip4 zone */
	if(!lz_exists(zones, "127.in-addr.arpa.") &&
		!lz_nodefault(cfg, "127.in-addr.arpa.")) {
		if(!(z=lz_enter_zone(zones, "127.in-addr.arpa.", "static", 
			LDNS_RR_CLASS_IN)) ||
		   !lz_enter_rr_into_zone(z,
			"127.in-addr.arpa. 10800 IN NS localhost.") ||
		   !lz_enter_rr_into_zone(z,
			"127.in-addr.arpa. 10800 IN SOA localhost. "
			"nobody.invalid. 1 3600 1200 604800 10800") ||
		   !lz_enter_rr_into_zone(z,
			"1.0.0.127.in-addr.arpa. 10800 IN PTR localhost.")) {
			log_err("out of memory adding default zone");
			if(z) { lock_rw_unlock(&z->lock); }
			return 0;
		}
		lock_rw_unlock(&z->lock);
	}
	/* reverse ip6 zone */
	if(!lz_exists(zones, "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.ip6.arpa.") &&
		!lz_nodefault(cfg, "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.ip6.arpa.")) {
		if(!(z=lz_enter_zone(zones, "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.ip6.arpa.", "static", 
			LDNS_RR_CLASS_IN)) ||
		   !lz_enter_rr_into_zone(z,
			"1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.ip6.arpa. 10800 IN NS localhost.") ||
		   !lz_enter_rr_into_zone(z,
			"1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.ip6.arpa. 10800 IN SOA localhost. "
			"nobody.invalid. 1 3600 1200 604800 10800") ||
		   !lz_enter_rr_into_zone(z,
			"1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.ip6.arpa. 10800 IN PTR localhost.")) {
			log_err("out of memory adding default zone");
			if(z) { lock_rw_unlock(&z->lock); }
			return 0;
		}
		lock_rw_unlock(&z->lock);
	}
	/* onion. zone (RFC 7686) */
	if(!add_empty_default(zones, cfg, "onion.")) {
		log_err("out of memory adding default zone");
		return 0;
	}
	/* test. zone (RFC 7686) */
	if(!add_empty_default(zones, cfg, "test.")) {
		log_err("out of memory adding default zone");
		return 0;
	}
	/* invalid. zone (RFC 7686) */
	if(!add_empty_default(zones, cfg, "invalid.")) {
		log_err("out of memory adding default zone");
		return 0;
	}
	/* block AS112 zones, unless asked not to */
	if(!cfg->unblock_lan_zones) {
		for(zstr = as112_zones; *zstr; zstr++) {
			if(!add_empty_default(zones, cfg, *zstr)) {
				log_err("out of memory adding default zone");
				return 0;
			}
		}
	}
	return 1;
}