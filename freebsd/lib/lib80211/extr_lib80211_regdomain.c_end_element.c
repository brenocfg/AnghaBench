#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mystate {size_t level; int /*<<< orphan*/ ** sbuf; TYPE_1__* country; int /*<<< orphan*/  parser; int /*<<< orphan*/ * curband; TYPE_4__* netband; TYPE_3__* rd; TYPE_2__* freqband; } ;
struct TYPE_8__ {scalar_t__ maxPower; scalar_t__ maxPowerDFS; int /*<<< orphan*/ * band; void* maxAntGain; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {void* sku; void* name; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; void* chanSep; void* chanWidth; void* freqEnd; void* freqStart; } ;
struct TYPE_5__ {int /*<<< orphan*/ * rd; int /*<<< orphan*/ * name; void* code; } ;

/* Variables and functions */
 int NO_COUNTRY ; 
 int /*<<< orphan*/  XML_GetCurrentLineNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_flag (struct mystate*,char*,int) ; 
 scalar_t__ iseq (char const*,char*) ; 
 char* sbuf_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_finish (int /*<<< orphan*/ *) ; 
 int sbuf_len (int /*<<< orphan*/ *) ; 
 void* strdup (char*) ; 
 void* strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

__attribute__((used)) static void
end_element(void *data, const char *name)
{
#define	iseq(a,b)	(strcasecmp(a,b) == 0)
	struct mystate *mt;
	int len;
	char *p;

	mt = data;
	sbuf_finish(mt->sbuf[mt->level]);
	p = sbuf_data(mt->sbuf[mt->level]);
	len = sbuf_len(mt->sbuf[mt->level]);

	/* <freqband>...</freqband> */
	if (iseq(name, "freqstart") && mt->freqband != NULL) {
		mt->freqband->freqStart = strtoul(p, NULL, 0);
		goto done;
	}
	if (iseq(name, "freqend") && mt->freqband != NULL) {
		mt->freqband->freqEnd = strtoul(p, NULL, 0);
		goto done;
	}
	if (iseq(name, "chanwidth") && mt->freqband != NULL) {
		mt->freqband->chanWidth = strtoul(p, NULL, 0);
		goto done;
	}
	if (iseq(name, "chansep") && mt->freqband != NULL) {
		mt->freqband->chanSep = strtoul(p, NULL, 0);
		goto done;
	}
	if (iseq(name, "flags")) {
		if (mt->freqband != NULL)
			mt->freqband->flags |= decode_flag(mt, p, len);
		else if (mt->netband != NULL)
			mt->netband->flags |= decode_flag(mt, p, len);
		else {
			warnx("flags without freqband or netband at line %ld ignored",
			    XML_GetCurrentLineNumber(mt->parser));
		}
		goto done;
	}

	/* <rd> ... </rd> */
	if (iseq(name, "name") && mt->rd != NULL) {
		mt->rd->name = strdup(p);
		goto done;
	}
	if (iseq(name, "sku") && mt->rd != NULL) {
		mt->rd->sku = strtoul(p, NULL, 0);
		goto done;
	}
	if (iseq(name, "netband") && mt->rd != NULL) {
		mt->curband = NULL;
		goto done;
	}

	/* <band> ... </band> */
	if (iseq(name, "freqband") && mt->netband != NULL) {
		/* XXX handle inline freqbands */
		goto done;
	}
	if (iseq(name, "maxpower") && mt->netband != NULL) {
		mt->netband->maxPower = strtoul(p, NULL, 0);
		goto done;
	}
	if (iseq(name, "maxpowerdfs") && mt->netband != NULL) {
		mt->netband->maxPowerDFS = strtoul(p, NULL, 0);
		goto done;
	}
	if (iseq(name, "maxantgain") && mt->netband != NULL) {
		mt->netband->maxAntGain = strtoul(p, NULL, 0);
		goto done;
	}

	/* <country>...</country> */
	if (iseq(name, "isocc") && mt->country != NULL) {
		mt->country->code = strtoul(p, NULL, 0);
		goto done;
	}
	if (iseq(name, "name") && mt->country != NULL) {
		mt->country->name = strdup(p);
		goto done;
	}

	if (len != 0) {
		warnx("unexpected XML token \"%s\" data \"%s\" at line %ld",
		    name, p, XML_GetCurrentLineNumber(mt->parser));
		/* XXX goto done? */
	}
	/* </freqband> */
	if (iseq(name, "freqband") && mt->freqband != NULL) {
		/* XXX must have start/end frequencies */
		/* XXX must have channel width/sep */
		mt->freqband = NULL;
		goto done;
	}
	/* </rd> */
	if (iseq(name, "rd") && mt->rd != NULL) {
		mt->rd = NULL;
		goto done;
	}
	/* </band> */
	if (iseq(name, "band") && mt->netband != NULL) {
		if (mt->netband->band == NULL) {
			warnx("no freqbands for band at line %ld",
			   XML_GetCurrentLineNumber(mt->parser));
		}
		if (mt->netband->maxPower == 0) {
			warnx("no maxpower for band at line %ld",
			   XML_GetCurrentLineNumber(mt->parser));
		}
		/* default max power w/ DFS to max power */
		if (mt->netband->maxPowerDFS == 0)
			mt->netband->maxPowerDFS = mt->netband->maxPower;
		mt->netband = NULL;
		goto done;
	}
	/* </netband> */
	if (iseq(name, "netband") && mt->netband != NULL) {
		mt->curband = NULL;
		goto done;
	}
	/* </country> */
	if (iseq(name, "country") && mt->country != NULL) {
		/* XXX NO_COUNTRY should be in the net80211 country enum */
		if ((int) mt->country->code == NO_COUNTRY) {
			warnx("no ISO cc for country at line %ld",
			   XML_GetCurrentLineNumber(mt->parser));
		}
		if (mt->country->name == NULL) {
			warnx("no name for country at line %ld",
			   XML_GetCurrentLineNumber(mt->parser));
		}
		if (mt->country->rd == NULL) {
			warnx("no regdomain reference for country at line %ld",
			   XML_GetCurrentLineNumber(mt->parser));
		}
		mt->country = NULL;
		goto done;
	}
done:
	sbuf_delete(mt->sbuf[mt->level]);
	mt->sbuf[mt->level--] = NULL;
#undef iseq
}