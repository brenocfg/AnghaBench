ATF_TC_BODY(fpsetround_basic, tc)
{

#ifndef _FLOAT_IEEE754
	atf_tc_skip("Test not applicable on this architecture.");
#else
	int r;

	ATF_CHECK_EQ(r = fpgetround(), FP_RN);
	if (FP_RN != r)
		fprintf(stderr, "default expected=%s got=%s\n", getname(FP_RN),
		    getname(r));
	ATF_CHECK_EQ(FLT_ROUNDS, 1);

	for (size_t i = 0; i < __arraycount(rnd); i++) {
		const size_t j = (i + 1) & 3;
		const int o = rnd[i].rm;
		const int n = rnd[j].rm;

		ATF_CHECK_EQ(r = fpsetround(n), o);
		if (o != r)
			fprintf(stderr, "set %s expected=%s got=%s\n",
			    getname(n), getname(o), getname(r));
		ATF_CHECK_EQ(r = fpgetround(), n);
		if (n != r)
			fprintf(stderr, "get expected=%s got=%s\n", getname(n),
			    getname(r));
		ATF_CHECK_EQ(r = FLT_ROUNDS, rnd[j].rf);
		if (r != rnd[j].rf)
			fprintf(stderr, "rounds expected=%x got=%x\n",
			    rnd[j].rf, r);
		test(r);
	}
#endif /* _FLOAT_IEEE754 */
}